# pyenvを導入する

* pyenvを導入し、python 3.12.0をインストールする手順

```
sh setup_pyenv.sh

# .bashrcの設定を現在のシェルに反映させる
source .bashrc

# python 3.12.0 のインストール
# 依存関係
sudo apt-get install libbz2-dev libncurses-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev liblzma-dev tk-dev -y
# python 3.12.0
pyenv install 3.12.0 -f

```



