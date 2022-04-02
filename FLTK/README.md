# FLTK
Creates simple GUI app using FLTK library

In order to make some .so files visible for the linker:
- Locate lib location:
```
locate Xinerama.so
```
- Create the link in the '/usr/lib/'
```
sudo ln -s /usr/lib/x86_64-linux-gnu/libXinerama.so.1 /usr/lib/libXinerama.so
```
