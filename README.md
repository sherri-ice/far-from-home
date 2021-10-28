# Far from home

## About game
Help kittens get home!

## Gameplay
### Menu
![](/home/sherri.ice/Pictures/menu.jpg)

### Kittens
####Main kitten:
![](/home/sherri.ice/Pictures/kitten.jpg)
You can navigate your cat using _keyboard arrows._

####Collect kittens:


![](/home/sherri.ice/Pictures/kittens.jpg)


Your cat has visibility area in code:
![](/home/sherri.ice/Pictures/radius.jpg)
Inside circle defines trigger border for cats: if kitten came up close than 
it will be added to _group_.

Outside circle defines _the group border_: kittens can move freely in group 
boarder.

If kitten gone out of group border _it leaves the group._

### Health
Cat has health. Indicator is in the top of the screen:

![](/home/sherri.ice/Downloads/full.jpg)

It decreases due to game process:

![](/home/sherri.ice/Downloads/middle_health.jpg)


 If no health left you will die :(

![](/home/sherri.ice/Downloads/no_healtj.jpg)

Death screen:

![](/home/sherri.ice/Downloads/die.jpg)


### Food
To increase your health you can eat some delicious food!
![](/home/sherri.ice/Pictures/food.jpg)

### Enemies
#### Dog
![](/home/sherri.ice/Pictures/dog.jpg)
Despite its cuties it's your enemy!

If dog detects you it will attack. 
Dog attack causes health decreasing. And all group cats get scared and run away!

### Portals

They are hidden in trees. To send your cat to search click on tree.
![](/home/sherri.ice/Pictures/portak.jpg)

### Map

[comment]: <> (By pressing key `Q` and)

## Build

###Required libs:

[Qt 5](https://www.qt.io/ "Qt's homepage")

###  CMakeList
You should specify your _Qt 5_ place:

`set(CMAKE_PREFIX_PATH "~/your/path/to/qt/Qt5/")`

For example:

`set(CMAKE_PREFIX_PATH "~/Qt/5.12.11/gcc_64/lib/cmake/Qt5/")`

Also, you should specify Qt libraries which are used:

`set(REQUIRED_LIBS Core Gui Widgets Multimedia MultimediaWidgets)`

`set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widget Qt5::Multimedia)`

[CMakeLists.txt Example](https://www.qt.io/ "CMakeLists.txt Example")

## Dev notes

[comment]: <> (Coming soon)
#
Game was designed by **"Bez-bab"** team as university project.