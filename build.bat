mkdir build
cd build
cmake -G"Visual Studio 10" -DGLFW_PATH="C:\Users\Jon Wayne\Development\glfw-lite" -DPHOENIX_PATH="C:\Users\Jon Wayne\Development\phoenixgl" -DBOX2D_PATH="C:\Users\Jon Wayne\Development\Box2D" -DBOOST_ROOT="C:\Program Files\boost\boost_1_43" -D_GLFW_WM_MOVE_HACK=TRUE ..