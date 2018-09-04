#!/usr/bin/perl

use strict;
use warnings;

use JSON;
use Switch;
use Data::Dumper;
use Getopt::Long;

my %int_offsets = (
    "u8" => 1,
    "s8" => 1,
    "u16" => 2,
    "s16" => 2,
    "u32" => 4,
    "s32" => 4,
    "u64" => 8,
    "s64" => 8
);

my $input = "";
my $output = "";

GetOptions("input|i=s" => \$input,
           "output|o=s" => \$output)
or die "Error in command line arguments\n";

my $header = "";
my $opcodes = "";

open(my $fd, '<', $input) or die "Unable to open file, $!\n";
my @entire_file=<$fd>;
close($fd) or warn "Unable to close the file handle: $!\n";

my $content = join('', @entire_file);
undef @entire_file;
chomp $content;

my $json = JSON::from_json($content);

my $namespace = $json->{'namespace'};
my $opcode = $json->{'opcode'};
my %messages = %{ $json->{'messages'} };

#########
# guard #
#########

my $unique_name = uc $namespace;
$unique_name =~ s/::/_/g;
my $guard = "TIVAN_" . $unique_name . "_H";

$header .= "#ifndef " . $guard . "\n";
$header .= "#define " . $guard . "\n\n";

$header .= "#include <groot.h>\n";
$header .= "#include <mantis.h>\n\n";

$header .= "%OPCODES%\n";

#############
# namespace #
#############

$header .= "namespace " . $namespace . " {\n\n";

foreach my $message_name (keys %messages) {
    my %schema = %{ $messages{$message_name} };
    my %fields = %{ $schema{'fields'} };

    ##########
    # opcode #
    ##########

    $opcodes .= "#define OPCODE_" . $unique_name . "_" . uc $message_name . " " . $opcode . "\n";
    ++$opcode;

    ##########
    # struct #
    ##########

    $header .= "\t";
    $header .= "class " . $message_name . " {\n";
    $header .= "%OFFSETS%";
    $header .= "\t\t";
    $header .= "const u8 *\t_data;\n";

    ########
    # ctor #
    ########

    $header .= "\t";
    $header .= "public:\n";
    $header .= "\t\t";
    $header .= "GR_DECLARE_SMARTPOINTERS(" . $message_name . ")\n";
    $header .= "\t\t";
    $header .= "GR_DELETE_ALL_DEFAULT(" . $message_name . ")\n";
    $header .= "\n";
    $header .= "\t\t";
    $header .= "explicit " . $message_name . "(const u8 *data) noexcept : _offsets {}, _data { data } {\n";
    $header .= "\t\t\t";
    $header .= "size_t offset = 0;\n";
    $header .= "\t\t\t";
    $header .= "for (size_t i = 0; i < FIELD_COUNT; ++i) { _offsets[i] = offset + 2; offset += 2 + static_cast<u16>(htons(*reinterpret_cast<const u16 *>(&_data[offset]))); }\n";
    $header .= "\t\t";
    $header .= "}\n";
    $header .= "\n";

    ##########
    # fields #
    ##########

    my $index = 0;
    my $offsets = "";

    foreach my $field_name (keys %fields) {
        my %typeinfo = %{ $fields{$field_name} };
        my $type = $typeinfo{'type'};

        $header .= "\t\t";
        switch ($type) {
            case ("uuid") {
                $header .= "groot::uuid::sptr get_" . $field_name . "() const noexcept { return groot::uuid::make_shared(&_data[_offsets[" . $index . "]]); }\n";
            }
            case (["u8","s8"]) {
                $header .= $type . " get_" . $field_name . "() const noexcept { return *reinterpret_cast<const " . $type . " *>(&_data[_offsets[" . $index . "]]); }\n";
            }
            case (["u16","s16"]) {
                $header .= $type . " get_" . $field_name . "() const noexcept { return static_cast<" . $type . ">(htons(*reinterpret_cast<const " . $type . " *>(&_data[_offsets[" . $index . "]]))); }\n";
            }
            case (["u32","s32"]) {
                $header .= $type . " get_" . $field_name . "() const noexcept { return static_cast<" . $type . ">(htonl(*reinterpret_cast<const " . $type . " *>(&_data[_offsets[" . $index . "]]))); }\n";
            }
            case (["u64","s64"]) {
                $header .= $type . " get_" . $field_name . "() const noexcept { return static_cast<" . $type . ">(htonll(*reinterpret_cast<const " . $type . " *>(&_data[_offsets[" . $index . "]]))); }\n";
            }
            case ("string") {
                $header .= "std::string_view get_" . $field_name . "() const noexcept { return { reinterpret_cast<const char *>(&_data[_offsets[" . $index . "]]) }; }\n";
            }
        }

        ++$index;
    }

    ###########
    # offsets #
    ###########

    $offsets .= "\t\t";
    $offsets .= "static constexpr size_t FIELD_COUNT { " . $index . " };\n";
    $offsets .= "\t\t";
    $offsets .= "size_t\t\t_offsets[FIELD_COUNT];\n";

    $header =~ s/%OFFSETS%/$offsets/g;

    $header .= "\t};\n\n";
}

#############
# namespace #
#############

$header .= "}\n\n";

#########
# guard #
#########

$header .= "#endif /* " . $guard . " */\n";

###########
# opcodes #
###########

$header =~ s/%OPCODES%/$opcodes/g;

########
# save #
########

open(my $fh, '>', $output . "/" . lc $unique_name . "_gen.h");
print $fh $header;
close $fh;

print "Done\n";

print $header;
