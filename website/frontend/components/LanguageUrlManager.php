<?php
/**
 * Created by PhpStorm.
 * User: Feo
 * Date: 23/08/2018
 * Time: 06:34
 */

namespace frontend\components;

use yii\web\UrlManager;
use frontend\models\Language;

class LanguageUrlManager extends UrlManager
{
    public function createUrl($params)
    {
        if (isset($params['lang_id'])) {
            $lang = Language::findOne($params['lang_id']);
            if ($lang === null) {
                $lang = Language::getDefaultLanguage();
            }

            unset($params['lang_id']);
        } else {
            $lang = Language::getCurrent();
        }

        $url = parent::createUrl($params);

        return $url == '/' ? '/'. $lang->code : '/'.$lang->code . $url;
    }
}
