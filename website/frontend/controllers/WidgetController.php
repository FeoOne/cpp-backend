<?php

namespace frontend\controllers;

class WidgetController extends \yii\web\Controller
{
    public function actionInvoice($amount)
    {
        $this->layout = '@app/views/layouts/widget';
        return $this->render('invoice', [
            'amount' => $amount,
        ]);
    }

}
