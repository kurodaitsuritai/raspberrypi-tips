# Bootloaderを更新する

* RaspberryPiが起動しなくなった場合に、Bootloaderを初期化すると起動するようになる場合がある。

* Raspberry Pi Imagerで、「OS」-「Misc utility images」-「Bootloader(Pi 5 family)」-「SD Card Boot」を選択して、SDカードにイメージを焼きこむ。（使用するSDカードは2GBでも問題ない）

* 作成されたSDカードでRaspberryPiを起動する。（Bootloaderが更新されたら画面一面に緑色が表示されるので、電源ボタン長押しで終了する）

* Raspberry Pi OSが焼きこまれたSDカードを用いて、RaspberryPiを起動する。

* ターミナルで、
    ```
    sudo -E rpi-eeprom-config --edit
    ```
    を入力する。

    「NET_INSTALL_AT_POWER_ON」がある場合は以下のように設定する（ピンク色の起動画面が表示されないようにするため）。

    ```
    NET_INSTALL_AT_POWER_ON=0
    ```

    Ctrl-S, Ctrl-Xでnanoを終了すると、自動的にEEPROMが更新される（OverlayFSが無効になっている必要あり）。




