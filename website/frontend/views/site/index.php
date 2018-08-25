<?php

use frontend\models\Content;

/* @var $this yii\web\View */

$this->title = 'BitPayment - Accept Payments in Cryptocurrencies';
?>
<section class="mdl-layout__tab-panel is-active bpt-body-section" id="scroll-tab-1">
    <div class="page-content">

        <div class="mdl-typography--text-center mdl-typography--subhead">
            <?= Content::t('index_about_teaser') ?>
        </div>

        <div class="mdl-typography--text-center">
        <button class="mdl-button mdl-js-button mdl-button--raised mdl-js-ripple-effect mdl-button--accent">
            Start using now
        </button>
        </div>

    </div>
</section>

<section class="mdl-layout__tab-panel" id="scroll-tab-2">
    <div class="page-content">
        Supported Coins
        <!-- Your content goes here -->
    </div>
</section>

<section class="mdl-layout__tab-panel" id="scroll-tab-3">
    <div class="page-content">
        Roadmap
        <!-- Your content goes here -->
    </div>
</section>

<section class="mdl-layout__tab-panel" id="scroll-tab-4">
    <div class="page-content">
        Roadmap
        <!-- Your content goes here -->
    </div>
</section>
