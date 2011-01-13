"------------------------------------------------------------------------------
" window settings 
"------------------------------------------------------------------------------

":set lines=60    " set lines   - sets height of window
":set columns=85  " set columns - sets width of window

"------------------------------------------------------------------------------
" tab settings 
"------------------------------------------------------------------------------

set expandtab    " expandtab  - insert spaces for tabs
set tabstop=2    " tabstop    - # of space chars inserted when tab pressed
set shiftwidth=2 " shiftwidth - # of space chars inserted for indentation 

filetype plugin indent on

"------------------------------------------------------------------------------
" color settings 
"------------------------------------------------------------------------------

":set t_Co=256
":let g:zenburn_high_Contrast = 1
":colorscheme zenburn
:hi search    ctermbg=223 ctermfg=238
:hi incsearch ctermbg=216 ctermfg=242

"------------------------------------------------------------------------------
" file settings
"------------------------------------------------------------------------------

set dir=~/.vim/swap " set swap directory

"------------------------------------------------------------------------------
" code settings
"------------------------------------------------------------------------------

" makeprg - sets the make program
"set makeprg=ant\ -quiet\ -emacs\ -find\ build.xml 

"cd ~/_perforce

"------------------------------------------------------------------------------
" misc settings
"------------------------------------------------------------------------------

set nu           " line numbers
set hlsearch     " highlight search

" status bar
set laststatus=2 
set statusline=%<%f\ %h%m%r%=%-14.(%l,%c%V%)\ %P

"------------------------------------------------------------------------------
" commands 
"------------------------------------------------------------------------------

nmap <C-K> <C-W><C-K><C-W><C-_> " move up split, maximize
nmap <C-J> <C-W><C-J><C-W><C-_> " move down split, maximize
nmap <C-z> :nohlsearch<Enter>   " clear search highlight

