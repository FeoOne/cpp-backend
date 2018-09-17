<?php

use yii\db\Migration;

/**
 * Class m180825_130218_merchant
 */
class m180825_130218_merchant extends Migration
{
    /**
     * {@inheritdoc}
     */
    public function safeUp()
    {
        $this->execute('CREATE TABLE merchant (
            id serial,
            user_id bigint,
            uuid uuid NOT NULL,
            PRIMARY KEY (id),
            FOREIGN KEY (user_id) REFERENCES "user"(id),
            UNIQUE (user_id),
            UNIQUE (uuid)
        );');

        $this->execute('CREATE TABLE shipment (
            id serial,
            merchant_id bigint,
            uuid uuid,
            name varchar(64) NOT NULL,
            keycode varchar(64) NOT NULL,
            PRIMARY KEY (id),
            FOREIGN KEY (merchant_id) REFERENCES merchant(id),
            UNIQUE (uuid)
        );');

        $this->execute('CREATE UNIQUE INDEX shipment_merchant_id_keycode_idx ON shipment(merchant_id,keycode);');

        $this->execute('ALTER TABLE shipment ADD COLUMN quantity int NOT NULL DEFAULT \'-1\';');

        $this->execute('ALTER TABLE shipment ADD COLUMN created_at integer NOT NULL, ADD COLUMN updated_at integer NOT NULL;');

        $this->execute('CREATE TABLE shipment_type (
            id serial,
            name varchar(32) NOT NULL,
            PRIMARY KEY (id),
            UNIQUE (name)
        );');

        $this->execute('INSERT INTO shipment_type(name) VALUES(\'float\');');

        $this->execute('ALTER TABLE shipment
            ADD COLUMN type bigint NOT NULL,
            ALTER COLUMN merchant_id SET NOT NULL,
            ALTER COLUMN uuid SET NOT NULL,
            ADD FOREIGN KEY (type) REFERENCES shipment_type(id);');

        return true;
    }

    /**
     * {@inheritdoc}
     */
    public function safeDown()
    {
        echo "m180825_130218_merchant cannot be reverted.\n";

        return false;
    }

    /*
    // Use up()/down() to run migration code without a transaction.
    public function up()
    {

    }

    public function down()
    {
        echo "m180825_130218_merchant cannot be reverted.\n";

        return false;
    }
    */
}
