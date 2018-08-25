class MessageBuilder {
    constructor() {
        this.buffer = new ArrayBuffer(1024);
        this.data = new DataView(this.buffer);
        this.offset = 0;
    }

    appendInt8(val) {
        const size = 1;
        this.appendSize(size);
        this.data.setInt8(this.offset, val);
        this.offset += size;
    }

    appendUInt8(val) {
        const size = 1;
        this.appendSize(size);
        this.data.setUint8(this.offset, val);
        this.offset += size;
    }

    appendInt16(val) {
        const size = 2;
        this.appendSize(size);
        this.data.setInt16(this.offset, val);
        this.offset += size;
    }

    appendUInt16(val) {
        const size = 2;
        this.appendSize(size);
        this.data.setUint16(this.offset, val);
        this.offset += size;
    }

    appendInt32(val) {
        const size = 4;
        this.appendSize(size);
        this.data.setInt32(this.offset, val);
        this.offset += size;
    }

    appendUInt32(val) {
        const size = 4;
        this.appendSize(size);
        this.data.setUint32(this.offset, val);
        this.offset += size;
    }

    appendUUID(val) {
        const size = 16;
        this.appendSize(size);
        let buffer = new Uint8Array(this.buffer, this.offset, size);
        buffer.set(val);
        this.offset += size;
    }

    appendString(val) {
        const size = val.length + 1;
        this.appendSize(size);
        let buffer = new Uint8Array(this.buffer, this.offset, size);
        for (let i = 0; i < val.length; ++i) {
            buffer[i] = val.charCodeAt(i);
        }
        buffer[val.length] = 0;
        this.offset += size;
    }

    appendSize(size) {
        console.log("appendSize(" + size + "), offset: " + this.offset);
        this.data.setUint16(this.offset, size);
        this.offset += 2;
    }

    build() {
        let buffer = new Uint8Array(this.buffer, 0, this.offset);
        let result = new Uint8Array(this.offset);
        result.set(buffer, 0);

        return result.buffer;
    }
}