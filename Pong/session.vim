let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Programs/DevProjects/TwentyGamesChallenge/Pong
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +16 src/pong.cpp
badd +48 CMakeLists.txt
badd +1 src/Game.hpp
badd +45 src/Game.cpp
badd +17 include/Game.hpp
badd +1 src/Entity.cpp
badd +0 include/Entity.hpp
argglobal
%argdel
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit src/pong.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 153 + 153) / 307)
exe 'vert 2resize ' . ((&columns * 153 + 153) / 307)
argglobal
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 16 - ((15 * winheight(0) + 40) / 81)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 16
normal! 028|
wincmd w
argglobal
if bufexists(fnamemodify("CMakeLists.txt", ":p")) | buffer CMakeLists.txt | else | edit CMakeLists.txt | endif
if &buftype ==# 'terminal'
  silent file CMakeLists.txt
endif
balt src/Game.hpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 46 - ((45 * winheight(0) + 40) / 81)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 46
normal! 048|
lcd ~/Programs/DevProjects/TwentyGamesChallenge/Pong
wincmd w
exe 'vert 1resize ' . ((&columns * 153 + 153) / 307)
exe 'vert 2resize ' . ((&columns * 153 + 153) / 307)
tabnext
edit ~/Programs/DevProjects/TwentyGamesChallenge/Pong/src/Game.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 153 + 153) / 307)
exe 'vert 2resize ' . ((&columns * 153 + 153) / 307)
argglobal
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 45 - ((44 * winheight(0) + 40) / 81)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 45
normal! 0
lcd ~/Programs/DevProjects/TwentyGamesChallenge/Pong
wincmd w
argglobal
if bufexists(fnamemodify("~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Game.hpp", ":p")) | buffer ~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Game.hpp | else | edit ~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Game.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Game.hpp
endif
balt ~/Programs/DevProjects/TwentyGamesChallenge/Pong/src/Game.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 5 - ((4 * winheight(0) + 40) / 81)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 5
normal! 0
lcd ~/Programs/DevProjects/TwentyGamesChallenge/Pong
wincmd w
exe 'vert 1resize ' . ((&columns * 153 + 153) / 307)
exe 'vert 2resize ' . ((&columns * 153 + 153) / 307)
tabnext
edit ~/Programs/DevProjects/TwentyGamesChallenge/Pong/src/Entity.cpp
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe 'vert 1resize ' . ((&columns * 153 + 153) / 307)
exe 'vert 2resize ' . ((&columns * 153 + 153) / 307)
argglobal
balt ~/Programs/DevProjects/TwentyGamesChallenge/Pong/src/Game.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 40) / 81)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Programs/DevProjects/TwentyGamesChallenge/Pong
wincmd w
argglobal
if bufexists(fnamemodify("~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Entity.hpp", ":p")) | buffer ~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Entity.hpp | else | edit ~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Entity.hpp | endif
if &buftype ==# 'terminal'
  silent file ~/Programs/DevProjects/TwentyGamesChallenge/Pong/include/Entity.hpp
endif
balt ~/Programs/DevProjects/TwentyGamesChallenge/Pong/src/Entity.cpp
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 1 - ((0 * winheight(0) + 40) / 81)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 1
normal! 0
lcd ~/Programs/DevProjects/TwentyGamesChallenge/Pong
wincmd w
exe 'vert 1resize ' . ((&columns * 153 + 153) / 307)
exe 'vert 2resize ' . ((&columns * 153 + 153) / 307)
tabnext 1
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let &winminheight = s:save_winminheight
let &winminwidth = s:save_winminwidth
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
