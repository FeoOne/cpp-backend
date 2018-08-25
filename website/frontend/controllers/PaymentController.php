<?php

namespace frontend\controllers;

class PaymentController extends \yii\web\Controller
{
    public function actionIndex()
    {
        return $this->render('index');
    }

    public function actionInvoice()
    {
        $this->layout = 'payment';

        $request = \Yii::$app->request;
        if (!YII_DEBUG && !$request->isPost) {
            throw new \yii\web\HttpException(405, 'Method not allowed.');
        }

        return $this->render('invoice');
    }

}
