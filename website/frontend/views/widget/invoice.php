<?php

use yii\helpers\Url;

/* @var $this yii\web\View */
/* @var $amount \phpDocumentor\Reflection\Types\Scalar */
?>

<button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect" id="checkout">
    Pay <?= $amount ?> BTC
</button>

<script type="text/javascript">
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

    let button = document.getElementById("checkout");
    button.addEventListener("click", function () {
        this.disabled = "disabled";

        const socket = new WebSocket('<?= Url::base('ws') ?>/api/v1/terminal');
        //const socket = new WebSocket('ws://127.0.0.1:8081/api/v1/terminal');
        socket.addEventListener('open', function (event) {
            const amount = "0.002";

            let uuid = new Uint8Array(16);
            uuid.fill(0, 0, 16);

            let builder = new MessageBuilder();
            builder.appendUUID(uuid);
            builder.appendUInt32(1);
            builder.appendString(amount);
            let message = builder.build();

            const header_size = 16;

            let buffer = new ArrayBuffer(header_size);

            let header = new DataView(buffer);
            header.setUint32(0, 0x31337FE0);
            header.setUint32(4, 0);
            header.setUint32(8, message.byteLength);
            header.setUint16(12, 10000);
            header.setUint16(14, 0);

            let packet = new Uint8Array(buffer.byteLength + message.byteLength);
            packet.set(new Uint8Array(buffer), 0);
            packet.set(new Uint8Array(message), buffer.byteLength);

            socket.send(packet);
            console.log('Opened');
        });

        socket.addEventListener('message', function (event) {
            console.log('Message from server ', event.data);
        });

        socket.addEventListener('close', function (event) {
            console.log('Closed');
        });

        socket.addEventListener('error', function (event) {
            console.log('error: ' + event.data);
        });
    });
</script>
