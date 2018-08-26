<?php

namespace frontend\controllers;

use \yii\web\HttpException;

class PaymentController extends \yii\web\Controller
{
    public function actionIndex()
    {
        return $this->render('index');
    }

    public function actionInvoice()
    {
        $this->layout = 'payment';

        $params = [];

        $request = \Yii::$app->request;
        if ($request->isPost) {
            // Create invoice

            // required arguments
            $merchant = $request->post('merchant');
            $shipment = $request->post('shipment');
            $quantity = $request->post('quantity');

            // optional arguments
            $currency = $request->post('currency');
            $cost = $request->post('cost');

            // argument validation
            if (is_null($merchant) || base64_encode(base64_decode($merchant, true)) !== $merchant){
                throw new HttpException(412, 'Payment processing error (1).');
            }
            $params[] = ['merchant' => $merchant];

            if (is_null($shipment) || base64_encode(base64_decode($shipment, true)) !== $shipment){
                throw new HttpException(412, 'Payment processing error (2).');
            }
            $params[] = ['shipment' => $shipment];

            if (is_null($quantity) || !is_numeric($quantity)) {
                throw new HttpException(412, 'Payment processing error (3).');
            }
            $quantity = (int)$quantity;
            if ($quantity < 0 || $quantity >= 1000000) { // @todo Remove hardcode.
                throw new HttpException(412, 'Payment processing error (4).');
            }
            $params[] = ['quantity' => $quantity];

            if (!is_null($currency)) {
                if (!is_numeric($currency)) {
                    throw new HttpException(412, 'Payment processing error (5).');
                }
                $currency = (int)$currency;
                if ($currency < 0 || $currency >= 32) { // @todo Remove hardcode.
                    throw new HttpException(412, 'Payment processing error (6).');
                }
                $params[] = ['currency' => $currency];
            }
            if (!is_null($cost)) {
                if (!is_numeric($cost)) {
                    throw new HttpException(412, 'Payment processing error (7).');
                }
                if ((float)$cost < 0) {
                    throw new HttpException(412, 'Payment processing error (8).');
                }
                $params[] = ['cost' => $cost];
            }
        } else {
            // Show incoice
        }

        return $this->render('invoice', $params);
    }

}
