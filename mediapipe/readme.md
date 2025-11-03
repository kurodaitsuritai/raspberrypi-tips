# mediapipeを使用する

* trixieの場合、インストールされているpythonのバージョンは3.13であるが、mediapipeが対応しているのは3.12までとなっている。

* そのため、pyenvを利用して、/home/pi/mediapipeフォルダのみ3.12が使用できるようにする。

```
cd /home/pi/mediapipe

pyenv local 3.12.0

pip install mediapipe

```


## モデル

<img src="https://ai.google.dev/static/mediapipe/images/solutions/pose_landmarks_index.png?hl=ja">
