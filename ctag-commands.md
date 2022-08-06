# Vim Commands: CTAGS

## Intro

- config file: ~/.ctags
- generate tags: `ctags`

## Commands

The tag file should exist.

- vim -t tagname - open the file where the tag is

- vim -t '/regex' - same as above but search for pattern

- Jump to tag underneath the cursor
    - CTRL+]
    - g]
    - :ta[g]
    - CTRL+rw

- :ts[elect] tagname - List the tags that match tagname

- :ts[select] - List tags that match last tagname from tag stack

- :pts[elect] tagname - (Preview Tag Select) Does :tselect and shows new tag in a "Preview" window horizontal 
split without moving the cursor.

-   CTRL+w} or :ptag CTRL+rw - Open preview window with the location of the tag definiton. 
Tag stack not updated as cursor does not move.

- ctrl+wz or :pc - Close preview window created by previous command.

- ctrl+w ctrl+] - open definition in horizontal split

- :tn and :tp - jump to next and previous matching tags.

- ctrl+t - jump back up in tag stack

- :tags - show contents of tag stack. Active entry marked with \>
