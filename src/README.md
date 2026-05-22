
# Serial通信(UART)について
    1. 各ヘッダーファイルにSerial.hをインクルード。
    2. Serials[定義した定数（Serial1→1）]->write("DATA");
        ↑これでSerial通信できる。Serial番号の定義はSerial.hで。


# コントローラーのデータ—
    1. 各ヘッダーファイルにreadController.hをインクルード。
    
    ボタンのtrue or false を確認したい。
        →Key2.values[代入値] == true でいける。
        代入するのは、//define KeyNumbersの Up, Down, Circle などを代入すれば確認できる。

    スティックについて
        L.とR.をclassで定義しています。（Lが左スティック、Rが右スティック）
        | x;    →スティックのx座標を取得（-128~127）
        | y;    →スティックのy座標を取得（-128~127）下が正。上が負。
        | Stickdeg()    →スティックの角度を取得（deg）  注意！スティックを倒していないと、-180が出力される（スティックを倒していないときを区別する方法は後述する。）
        | Stickpower()  →スティックがどれだけ中心から倒されているかを取得。（ sqrt(x^2 + y^2) を出力するだけです。）

        注意！！
            Stickdeg()で返される戻り値は、degです。（radianではない。）私の作った、convert.hにある、deg_radian(int deg)をご使用ください。

        スティックを倒していないときを区別する
``` c:main.c
    if (L.Stickpower >= 2)  ←２以上倒されている。
```


//


