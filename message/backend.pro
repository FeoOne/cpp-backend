namespace backend_messaging;

message handshake_request {
    message: string[16];
}

message handshake_response {
    message: bytes[16];
    version: u32;
}
