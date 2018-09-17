<?php

use yii\db\Migration;

/**
 * Class m180825_130652_l12n_data
 */
class m180825_130652_l12n_data extends Migration
{
    /**
     * {@inheritdoc}
     */
    public function safeUp()
    {
        $this->execute('INSERT INTO language(is_default, code, locale, name) VALUES(TRUE, \'en\', \'en-US\', \'English\');');
        $this->execute('INSERT INTO language(is_default, code, locale, name) VALUES(FALSE, \'ru\', \'ru-RU\', \'Русский\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'index_about_teaser\', \'«BitPayment» is a powerfull payment gateway for cryptocurrencies such as Bitcoin and Ethereum.\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'index_about_teaser\', \'«BitPayment» это богатый возможностями платежный терминал для криптовалют, вроде Bitcoin или Ethereum.\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_prepeare_page\', \'Prepearing page...\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_prepeare_page\', \'Подготовка страницы...\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_keep_calm\', \'Keep calm. It will not take long.\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_keep_calm\', \'Сохраняйте спокойствие. Это не займет много времени.\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_invalid_email\', \'Input is not a valid e-mail.\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_invalid_email\', \'Веденный e-mail некорректен.\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_item_purchasing\', \'Item You are Purchasing.\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_item_purchasing\', \'Товар, который Вы желаете приобрести.\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'btn_cancel\', \'Cancel\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'btn_cancel\', \'Отменить\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_complete_checkout\', \'Complete Checkout\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_complete_checkout\', \'Продолжть\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_contact_merchant\', \'Contact Merchant\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_contact_merchant\', \'Связаться с продавцом\');');

        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'invoice_require_email\', \'Information about the purchase and status of payment will be sent to the specified e-mail.\');');
        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'invoice_require_email\', \'На указанную почту будет выслана информация о покупке и статусе платежа.\');');

//        $this->execute('INSERT INTO content(language_id, key, value) VALUES(1, \'\', \'\');');
//        $this->execute('INSERT INTO content(language_id, key, value) VALUES(2, \'\', \'\');');

        return true;
    }

    /**
     * {@inheritdoc}
     */
    public function safeDown()
    {
        echo "m180825_130652_l12n_data cannot be reverted.\n";

        return false;
    }

    /*
    // Use up()/down() to run migration code without a transaction.
    public function up()
    {

    }

    public function down()
    {
        echo "m180825_130652_l12n_data cannot be reverted.\n";

        return false;
    }
    */
}
