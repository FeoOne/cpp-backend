<?php

use frontend\models\Content;

$this->registerJsFile('/js/invoice.js');

/* @var $this yii\web\View */
/* @var $merchant string */
/* @var $purchase string */
/* @var $quantity int */
/* @var $currency int */
/* @var $cost string */
?>

<div class=" invoice-body">
<div class="mdl-grid">
    <div class="mdl-cell mdl-cell--3-col"></div>
    <div class="mdl-cell mdl-cell--6-col">

        <div class="invoice-card-wide mdl-card mdl-shadow--2dp">
            <div class="mdl-card__title mdl-card--border">
                <h2 class="invoice-title">
                    <div class="mdl-card__title-text">«30 gems»</div>
                    <div class="mdl-card__subtitle-text"><?= Content::t('invoice_item_purchasing') ?></div>
                </h2>
            </div>
            <div class="mdl-card__supporting-text mdl-card--border invoice-supporting-text">
                <div class="mdl-typography--subhead">«Merchant Name»</div>
                <div>Merchant description.</div>
            </div>
            <div class="mdl-card__supporting-text invoice-supporting-text">

                <div class="mdl-textfield mdl-js-textfield mdl-textfield--floating-label">
                    <input class="mdl-textfield__input" type="email" id="buyer-mail">
                    <label class="mdl-textfield__label" for="buyer-mail">E-mail...</label>
                    <span class="mdl-textfield__error"><?= Content::t('invoice_invalid_email') ?></span>
                </div>

                <div><?= Content::t('invoice_require_email') ?></div>

            </div>
            <div class="mdl-card__actions mdl-card--border mdl-typography--text-right">
                <a class="mdl-button mdl-button--colored mdl-js-button mdl-js-ripple-effect mdl-button--accent"><?= Content::t('btn_cancel') ?></a>
                <a class="mdl-button mdl-button--colored mdl-js-button mdl-js-ripple-effect mdl-button--primary" disabled="disabled"><?= Content::t('invoice_complete_checkout') ?></a>
            </div>
            <div class="mdl-card__menu">
                <button class="mdl-button mdl-button--icon mdl-js-button mdl-js-ripple-effect mdl-button--colored" id="contact_merchant_button">
                    <i class="material-icons">mail_outline</i>
                </button>
                <div class="mdl-tooltip mdl-tooltip--left" data-mdl-for="contact_merchant_button"><?= Content::t('invoice_contact_merchant') ?></div>
            </div>
        </div>

    </div>
    <div class="mdl-cell mdl-cell--3-col"></div>
</div>
</div>

<?php
    if (isset($merchant) && isset($purchase) && isset($quantity)) {
        echo '<input type="hidden" id="merchant" value="' . $merchant . '">';
        echo '<input type="hidden" id="purchase" value="' . $purchase . '">';
        echo '<input type="hidden" id="quantity" value="' . $quantity . '">';
    }
    if (isset($currency)) {
        echo '<input type="hidden" id="currency" value="' . $currency . '">';
    }
    if (isset($cost)) {
        echo '<input type="hidden" id="cost" value="' . $cost . '">';
    }
