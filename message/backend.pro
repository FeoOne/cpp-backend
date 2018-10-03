namespace backend_messaging;

//opcode-offset: 10000;

message handshake_request {
    message: string[16];
}

message handshake_response {
    message: string[16];
    version: u32;
}
