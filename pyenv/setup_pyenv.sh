# !/bin/bash

# ホームディレクトリに移動
cd $HOME

# pyenvのインストールシェルをダウンロード・実行
sudo curl https://pyenv.run | bash

# .profile/.bashrcの編集
HAS_PYENV_ROOT=$(cat .profile | grep -i 'PYENV_ROOT')
if [ -z "$HAS_PYENV_ROOT"]; then
    echo '# for PYENV' >> .profile
    echo 'export PYENV_ROOT="$HOME/.pyenv"' >> .profile
    echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> .profile
    echo 'eval "$(pyenv init - bash)"' >> .profile
fi
HAS_PYENV_ROOT=$(cat .bashrc | grep -i 'PYENV_ROOT')
if [ -z "$HAS_PYENV_ROOT"]; then
    echo '# for PYENV' >> .bashrc
    echo 'export PYENV_ROOT="$HOME/.pyenv"' >> .bashrc
    echo '[[ -d $PYENV_ROOT/bin ]] && export PATH="$PYENV_ROOT/bin:$PATH"' >> .bashrc
    echo 'eval "$(pyenv init - bash)"' >> .bashrc
fi

# .bashrcの設定を現在のシェルに反映させる
source .bashrc

# python 3.12.0 のインストール
# 依存関係
sudo apt-get install libbz2-dev libncurses-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev liblzma-dev tk-dev -y
# python 3.12.0
pyenv install 3.12.0 -f


