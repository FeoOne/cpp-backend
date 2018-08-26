<?php

use yii\db\Migration;

/**
 * Class m180823_021225_l12n
 */
class m180823_021225_l12n extends Migration
{
    /**
     * {@inheritdoc}
     */
    public function safeUp()
    {
        $this->execute('CREATE TABLE language (
                id serial,
                is_default boolean NOT NULL DEFAULT FALSE,
                code character(2) NOT NULL,
                locale character varying(8) NOT NULL,
                name character varying(16) NOT NULL,
                PRIMARY KEY (id)
            );');

        $this->execute('CREATE TABLE content (
                id serial,
                language_id bigint NOT NULL,
                key varchar(32) NOT NULL,
                value text NOT NULL,
                description text,
                PRIMARY KEY (id),
                FOREIGN KEY (language_id) REFERENCES language(id)
            );');

        $this->execute('CREATE UNIQUE INDEX content_language_key_idx ON content (language_id, key);');

        return true;
    }

    /**
     * {@inheritdoc}
     */
    public function safeDown()
    {
        echo "m180823_021225_l12n cannot be reverted.\n";

        return false;
    }
}
