#!/usr/bin/fish

if test "$argv[1]" = "clean"
    echo "Cleaning up..."
    rm -fr build

    for cachefile in (find . -name "*-pygbag.*")
        rm $cachefile
    end
end

if test "$argv[2]" = "run"
    # pygbag --PYBUILD 3.13 --ume_block 0 --template noctx.tmpl --cdn https://pygame-web.github.io/pygbag/0.0/ src
    pygbag --PYBUILD 3.12 --ume_block 0 --template noctx.tmpl --cdn https://pygame-web.github.io/pygbag/0.0/ src
end