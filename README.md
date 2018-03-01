# WHAT
HVC-P2(http://www.fa.omron.co.jp/product/special/hvc-p2/)
をRaspberry Piなどで使うためのラッパーみたいなもの.

- プログラミング言語
    - C++
- ディレクトリの中身
    - cameraModule:Dockerfile
    - src:全てのプログラム

# プログラムの説明
- main.cpp
    - カメラモジュールを使うためのメインプログラム
    - 内部で自作クラスを使用してモジュールとやり取りしている
- CameraModule.cpp/hpp
    - カメラモジュールとやり取りするこのリポジトリのメイン
    - インスタンスを生成, 好きなコマンドを送信, レスポンスを解析の3つの手順でやり取りができる
- register.cpp loadAlbum.cpp
    - 顔認証機能, アルバムロード機能を単独で使うためのプログラム

# HOW TO USE
- compile
`make`
- docker コンテナを立ち上げる
`docker-compose up -d --build`
