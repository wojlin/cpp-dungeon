# cpp-dungeon
Pixel Dungeon, a C++ roguelike, combines challenging gameplay with minimalist ASCII graphics in procedurally generated dungeons. Navigate pixelated monsters and artifacts in turn-based style, offering a unique, nostalgic experience for fans of classic roguelike adventures.


## installation

```bash
git clone https://github.com/wojlin/cpp-dungeon.git
cd cpp-dungeon
git submodule add https://github.com/google/googletest.git external/googletest

pip install 'jinja2<3.1' gcovr # only needed to gen code coveragge report. you can skip this step
pip install gcovr
sudo pat-get install gcovr
pip install --upgrade gcovr
```

## build

```bash
mkdir build && cd build && cmake ..
make && make test
```

## test
```bash
make test
gcovr -r ../ -e ../external -e ../include -e ../test --html --html-theme github.dark-green --html-details -o dungeon.html
```