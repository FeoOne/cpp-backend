<?php

/* @var $this \yii\web\View */
/* @var $content string */

use yii\helpers\Html;
use frontend\assets\AppAsset;
use common\widgets\Alert;

AppAsset::register($this);
?>
<?php $this->beginPage() ?>
<!DOCTYPE html>
<html lang="<?= Yii::$app->language ?>" class="mdl-js">
<head>
    <meta charset="<?= Yii::$app->charset ?>">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <?= Html::csrfMetaTags() ?>
    <title><?= Html::encode($this->title) ?></title>
    <?php $this->head() ?>
</head>
<body class="">
<?php $this->beginBody() ?>

<div class="mdl-layout mdl-js-layout mdl-layout--fixed-header">
    <header class="mdl-layout__header">
        <div class="mdl-layout__header-row">
            <!-- Title -->
            <span class="mdl-layout-title">BitPayments</span>
        </div>
        <!-- Tabs -->
        <div class="mdl-layout__tab-bar mdl-js-ripple-effect">
            <a href="#scroll-tab-1" class="mdl-layout__tab is-active">About</a>
            <a href="#scroll-tab-2" class="mdl-layout__tab">Supported Coins</a>
            <a href="#scroll-tab-3" class="mdl-layout__tab">Roadmap</a>
        </div>
    </header>
    <div class="mdl-layout__drawer">
        <span class="mdl-layout-title">Title</span>
    </div>
    <main class="mdl-layout__content">
        <?= Alert::widget() ?>
        <?= $content ?>
    </main>

    <footer class="mdl-mega-footer">
        <div class="mdl-mega-footer__middle-section">

            <div class="mdl-mega-footer__drop-down-section">
                <input class="mdl-mega-footer__heading-checkbox" type="checkbox" checked>
                <h1 class="mdl-mega-footer__heading">Features</h1>
                <ul class="mdl-mega-footer__link-list">
                    <li><a href="#">About</a></li>
                    <li><a href="#">Terms</a></li>
                    <li><a href="#">Partners</a></li>
                    <li><a href="#">Updates</a></li>
                </ul>
            </div>

            <div class="mdl-mega-footer__drop-down-section">
                <input class="mdl-mega-footer__heading-checkbox" type="checkbox" checked>
                <h1 class="mdl-mega-footer__heading">Details</h1>
                <ul class="mdl-mega-footer__link-list">
                    <li><a href="#">Specs</a></li>
                    <li><a href="#">Tools</a></li>
                    <li><a href="#">Resources</a></li>
                </ul>
            </div>

            <div class="mdl-mega-footer__drop-down-section">
                <input class="mdl-mega-footer__heading-checkbox" type="checkbox" checked>
                <h1 class="mdl-mega-footer__heading">Technology</h1>
                <ul class="mdl-mega-footer__link-list">
                    <li><a href="#">How it works</a></li>
                    <li><a href="#">Patterns</a></li>
                    <li><a href="#">Usage</a></li>
                    <li><a href="#">Products</a></li>
                    <li><a href="#">Contracts</a></li>
                </ul>
            </div>

            <div class="mdl-mega-footer__drop-down-section">
                <input class="mdl-mega-footer__heading-checkbox" type="checkbox" checked>
                <h1 class="mdl-mega-footer__heading">FAQ</h1>
                <ul class="mdl-mega-footer__link-list">
                    <li><a href="#">Questions</a></li>
                    <li><a href="#">Answers</a></li>
                    <li><a href="#">Contact us</a></li>
                </ul>
            </div>

        </div>

        <div class="mdl-mega-footer__bottom-section">
            &copy; «<?= Html::encode(Yii::$app->name) ?>» <?= date('Y') ?>
        </div>

    </footer>
</div>

<?php $this->endBody() ?>
</body>
</html>
<?php $this->endPage() ?>
