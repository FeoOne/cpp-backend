namespace backend_database;

opcode_offset: 10000;

message handshake_request {
    message: string;
}

message handshake_response {
    data: u8[16];
}
