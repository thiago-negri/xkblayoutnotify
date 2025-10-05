Emits the current XkbLayout group to stdout, will emit new lines every time the
layout changes.

I'm using this to pipe into dzen2 to show my current keyboard layout in a status
bar.

For example:

```sh
xkblayoutnotify | \
  awk '{print $2; fflush();}' | \
  while read g; do case $g in \
    0) echo "us";; \
    1) echo "intl";; \
  esac; done | \
  dzen2
```

My complete configuration is in [herbstluftwm/panel.sh](https://github.com/thiago-negri/dotfiles/blob/master/.config/herbstluftwm/panel.sh)

To build, run `make`, you need X11 development libraries.
