if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <S-Insert> 
cmap <S-Insert> +
xnoremap  ggVG
snoremap  gggHG
onoremap  gggHG
nnoremap  gggHG
vnoremap  "+y
noremap  h
map 	 :
noremap <NL> j
noremap  k
noremap  l
vnoremap  :update
nnoremap  :update
onoremap  :update
vnoremap  "+x
map   /
vnoremap $w `>a"`<i"
vnoremap $q `>a'`<i'
vnoremap $$ `>a"`<i"
vnoremap $3 `>a}`<i{
vnoremap $2 `>a]`<i[
vnoremap $1 `>a)`<i(
map ,mbt <Plug>TMiniBufExplorer
map ,mbu <Plug>UMiniBufExplorer
map ,mbc <Plug>CMiniBufExplorer
map ,mbe <Plug>MiniBufExplorer
nmap ,ihn :IHN
nmap ,is :IHS:A
nmap ,ih :IHS
noremap ,m :%s/\r//g
map ,t :Tlist
map ,s? z=
map ,sa zg
map ,sp [
map ,sn ]
map ,q :e ~/buffer
map ,tm :tabmove 
map ,tc :tabclose
map ,tn :tabnew %
map ,bd :Bclose
nmap ,fu :se ff=unix
nmap ,fd :se ff=dos
nmap ,w :w!
map 0 ^
imap ° 0i
imap ¤ $a
map Q gq
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
map <F2> :%s/s*$//g:noh''
map <F9> ggVGg?
map <Left> :bp
map <Right> :bn
vmap <S-Insert> 
nmap <S-Insert> "+gP
omap <S-Insert> "+gP
vnoremap <C-Insert> "+y
vnoremap <S-Del> "+x
vnoremap <BS> d
map <C-Space> ?
cnoremap  <Home>
inoremap  gggHG
cnoremap  <End>
cnoremap  
inoremap  :update
inoremap #m :r $HOME/.vim/template/c.txt
inoremap $c /** **/O
cnoremap $td tabnew ~/Desktop/
cnoremap $th tabnew ~/
cnoremap $tc <C->eCurrentFileDir("tabnew")
cnoremap $c e <C->eCurrentFileDir("e")
cnoremap $q <C->eDeleteTillSlash()
imap ,ihn :IHN
imap ,is :IHS:A
imap ,ih :IHS
vmap ë :m'<-2`>my`<mzgv`yo`z
vmap ê :m'>+`<my`>mzgv`yo`z
nmap ë mz:m-2`z
nmap ê mz:m+`z
iabbr xdate =strftime("%Y-%m-%d %H:%M:%S")
let &cpo=s:cpo_save
unlet s:cpo_save
set ambiwidth=double
set autoindent
set autoread
set backspace=eol,start,indent
set backupdir=/tmp
set cindent
set cmdheight=2
set completeopt=menu
set cscopetag
set cscopeverbose
set directory=/tmp
set noequalalways
set errorformat=%f:%l:%m
set expandtab
set fileencodings=ucs-bom,utf-8,chinese
set helplang=cn
set hidden
set history=400
set hlsearch
set incsearch
set langmenu=en_gb.utf-8
set laststatus=2
set matchtime=4
set nomodeline
set mouse=a
set ruler
set scrolloff=3
set shiftwidth=4
set showcmd
set showmatch
set smartcase
set smartindent
set smarttab
set softtabstop=4
set statusline=%f\ %h%1*%m%r%w%0*\ [%{strlen(&ft)?&ft:'none'},%{&fileencoding},%{&fileformat}]\ CWD:%r%{CurDir()}%h\ Pos:%l-%c[%L]
set suffixes=.bak,~,.o,.h,.info,.swp,.obj,.info,.aux,.log,.dvi,.bbl,.out,.o,.lo
set noswapfile
set tabstop=4
set textwidth=500
set viminfo='10,
set whichwrap=b,s,<,>,h,l
set wildmenu
set nowritebackup
" vim: set ft=vim :
