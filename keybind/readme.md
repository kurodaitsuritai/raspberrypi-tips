# キーバインドを変更する

## trixi - labwc の場合

* .config/labwc/rc.xmlを編集する

* パワーボタンを「再起動」に割当て、また、起動時のnumlockをONにする設定の例

```
<?xml version="1.0"?>
<openbox_config xmlns="http://openbox.org/3.4/rc">
    <keyboard>
        <numlock>on</numlock>
        <keybind key="XF86PowerOff" onRelease="yes">
            <action name="Execute">
	        <command>sudo reboot</command>
            </action>
        </keybind>
    </keyboard>
</openbox_config>
```