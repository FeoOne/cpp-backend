<?php

namespace frontend\models;

use Yii;

/**
 * This is the model class for table "public.language".
 *
 * @property int $id
 * @property bool $is_default
 * @property string $code
 * @property string $locale
 * @property string $name
 */
class Language extends \yii\db\ActiveRecord
{
    /**
     * {@inheritdoc}
     */
    public static function tableName()
    {
        return 'language';
    }

    /**
     * {@inheritdoc}
     */
    public function rules()
    {
        return [
            [['is_default'], 'boolean'],
            [['code', 'locale', 'name'], 'required'],
            [['code'], 'string', 'max' => 2],
            [['locale'], 'string', 'max' => 8],
            [['name'], 'string', 'max' => 16],
        ];
    }

    /**
     * {@inheritdoc}
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'is_default' => 'Is Default',
            'code' => 'Code',
            'locale' => 'Locale',
            'name' => 'Name',
        ];
    }

    static $current = null;

    static function getCurrent()
    {
        if (self::$current === null) {
            self::$current = self::getDefaultLanguage();
        }
        return self::$current;
    }

    static function setCurrent($code = null)
    {
        $language = self::getLanguageByCode($code);
        self::$current = ($language === null) ? self::getDefaultLanguage() : $language;
        Yii::$app->language = self::$current->locale;
    }

    static function getDefaultLanguage()
    {
        return Language::find()->where('is_default = :default', [ ':default' => true ])->one();
    }

    static function getLanguageByCode($code = null)
    {
        $result = null;
        if ($code != null) {
            $language = Language::find()->where('code = :code', [ ':code' => $code ])->one();
            if ($language != null) {
                $result = $language;
            }
        }
        return $result;
    }
}
