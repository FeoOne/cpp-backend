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

        const socket = new WebSocket('<?= Url::base('ws') ?>/api/v1/terminal');
    });
</script>
