<?php

namespace frontend\models;

use Yii;

/**
 * This is the model class for table "content".
 *
 * @property int $id
 * @property int $language_id
 * @property string $key
 * @property string $value
 * @property string $description
 *
 * @property Language $language
 */
class Content extends \yii\db\ActiveRecord
{
    /**
     * {@inheritdoc}
     */
    public static function tableName()
    {
        return 'content';
    }

    /**
     * {@inheritdoc}
     */
    public function rules()
    {
        return [
            [['language_id', 'key', 'value'], 'required'],
            [['language_id'], 'default', 'value' => null],
            [['language_id'], 'integer'],
            [['value', 'description'], 'string'],
            [['key'], 'string', 'max' => 32],
            [['language_id', 'key'], 'unique', 'targetAttribute' => ['language_id', 'key']],
            [['language_id'], 'exist', 'skipOnError' => true, 'targetClass' => Language::className(), 'targetAttribute' => ['language_id' => 'id']],
        ];
    }

    /**
     * {@inheritdoc}
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'language_id' => 'Language ID',
            'key' => 'Key',
            'value' => 'Value',
            'description' => 'Description',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getLanguage()
    {
        return $this->hasOne(Language::className(), ['id' => 'language_id']);
    }

    public static function t($key)
    {
        $language = Language::getCurrent();
        $result = $key;
        $content = Content::find()->where(['language_id' => $language->getAttribute('id'), 'key' => $key])->one();
        if ($content != null) {
            $result = $content->getAttribute('value');
        }
        return $result;
    }
}
