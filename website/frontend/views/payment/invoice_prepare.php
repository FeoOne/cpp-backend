<?php

use frontend\models\Content;

$this->registerJsFile('/js/invoice.js');

/* @var $this yii\web\View */
?>
<div class="mdl-progress mdl-js-progress mdl-progress__indeterminate" style="width:100%;height:3px;"></div>
<br><br><br><br>
<div class="mdl-typography--text-center">
    <span class="mdl-typography--body-2"><?= Content::t('invoice_prepeare_page') ?></span>
    <br>
    <?= Content::t('invoice_keep_calm') ?>
</div>

<input type="hidden" id="q_currency" value="<?= '' ?>">
<input type="hidden" id="q_amount" value="<?= '' ?>">

<form action="https://bitpt.net/invoice/" method="post" rel="noreferrer">
    <input type="hidden" name="merchant" value="L9ThxnotKPzthJ7hu3bnORuT6xI=">
    <input type="hidden" name="shipment" value="3p8sf9JeGzr60+haC9F9mxANtLM=">
    <input type="hidden" name="quantity" value="1">
    <input type="submit">
</form>
