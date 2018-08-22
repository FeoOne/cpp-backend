<?php

namespace frontend\assets;

use yii\web\AssetBundle;

/**
 * Main frontend application asset bundle.
 */
class AppAsset extends AssetBundle
{
    public $basePath = '@webroot';
    public $baseUrl = '@web';
    public $css = [
        'css/site.css',
        'https://fonts.googleapis.com/icon?family=Material+Icons',
        'http://fonts.googleapis.com/css?family=Roboto:400,100,500,300italic,500italic,700italic,900,300',
        'https://code.getmdl.io/1.3.0/material.brown-blue.min.css',
    ];
    public $js = [
    ];
    public $depends = [
        'rafaelvaloto\mdl\material\MaterialDesignLiteAsset',
    ];
}
