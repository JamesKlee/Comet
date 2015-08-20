set exrc
set secure

set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab

set autoindent
set cindent

execute pathogen#infect()
syntax on
set background=dark
colorscheme solarized

set relativenumber
set number
set ruler

autocmd CursorMovedI * if pumvisible() == 0|pclose|endif
autocmd InsertLeave * if pumvisible() == 0|pclose|endif

let g:ycm_global_ycm_extra_conf = "~/.vim/.ycm_extra_conf.py"
