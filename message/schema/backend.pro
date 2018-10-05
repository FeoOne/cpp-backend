namespace backend_database;

opcode_offset: 10000;

message handshake_request {
    message: string;
    field: u32;
}

message handshake_response {
    message: string;
    field: u64;
}
