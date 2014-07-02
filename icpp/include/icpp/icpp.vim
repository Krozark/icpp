" Vim syntax file
" Language:	icpp
" Current Maintainer:	Maxime Barbier
" Last Change:	2014 jun 14

" Quit when a (custom) syntax file was already loaded
if exists("b:current_syntax")
  finish
endif

" We need nocompatible mode in order to continue lines with backslashes.
" Original setting will be restored.
let s:cpo_save = &cpo
set cpo&vim

syn keyword icppSpecial         exit source
syn keyword icppFlags           flags link
syn keyword icppStatement       run compile
syn keyword icppOperator        as with detached
syn keyword icppBuiltin         help show print delete wget
syn keyword icppImport          from import
syn keyword icppType            char bool int float double string
syn keyword icppStorage         auto const
syn keyword icppConstant        true false null
syn keyword icppTodo            FIXME NOTE NOTES TODO XXX contained


" Integer with - + or nothing in front
syn match icppNumber '\<\d\+'
syn match icppNumber '[-+]\d\+'
" Floating point number with decimal no E or e (+,-)
syn match icppNumber '\d\+\.\d*'
syn match icppNumber '[-+]\d\+\.\d*'
" Floating point like number with E and no decimal point (+,-)
syn match icppNumber '[-+]\=\d[[:digit:]]*[eE][\-+]\=\d\+'
syn match icppNumber '\d[[:digit:]]*[eE][\-+]\=\d\+'
" Floating point like number with E and decimal point (+,-)
syn match icppNumber '[-+]\=\d[[:digit:]]*\.\d*[eE][\-+]\=\d\+'
syn match icppNumber '\d[[:digit:]]*\.\d*[eE][\-+]\=\d\+'

syn region icppString start='"' end='"'
syn region icppChar start='\'' end='\''

syn match icppComment "\/\/.*$" contains=icppTodo
syn region icppComment	matchgroup=cCommentStart start="/\*" end="\*/" contains=icppTodo extend

hi def link icppSpecial     Special
hi def link icppFlags       Special
hi def link icppStatement   Statement
hi def link icppOperator    Operator
hi def link icppBuiltin     Function
hi def link icppImport      Include
hi def link icppType        Type
hi def link icppStorage     StorageClass
hi def link icppConstant    Constant
hi def link icppTodo        Todo
hi def link icppNumber      Number
hi def link icppChar        Number
hi def link icppString      String
hi def link icppComment     Comment

let b:current_syntax = "icpp"

let &cpo = s:cpo_save
unlet s:cpo_save

