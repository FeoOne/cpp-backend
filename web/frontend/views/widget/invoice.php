<?php

use yii\helpers\Url;

/* @var $this yii\web\View */
/* @var $amount \phpDocumentor\Reflection\Types\Scalar */
?>

<button class="mdl-button mdl-js-button mdl-button--raised mdl-button--colored mdl-js-ripple-effect" id="checkout">
    Pay <?= $amount ?> BTC
</button>

<script type="text/javascript">
    let button = document.getElementById("checkout");
    button.addEventListener("click", function () {
        this.disabled = "disabled";

        //const socket = new WebSocket('<?= Url::base('ws') ?>/api/v1/terminal');
        const socket = new WebSocket('ws://127.0.0.1:8081/api/v1/terminal');
        socket.addEventListener('open', function (event) {
            socket.send('123');
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
