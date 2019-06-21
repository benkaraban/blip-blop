# Forker's notes

I am mainly trying to modernize the code. Both in terms of C++ features, and
features (mainly trying not to lock the game in 640x480, adding a few shaders
and stuff).

As the code is kinda old, there's a lot of revamping to do, and a lot of
optimizations done back in the days shouldn't be relevant anymore. The code
contains a FUCKTON of global variables, to the point where I'm in awe that
somehow the game works flawlessly. The quantity of global variables declared
and handled all over the places is truly unmanageable.

As a french, I can work my way through the code, and although I'll be
translating comments as I skim through it, there are some really funny gems
that I'd rather not translate as they'd break the stupidity that made Blip'n
Blop famous. I would rather have a separate lexicon for the fellas that can't
french.

This project is HUGE for two students. Kudos to you guys, it's a LOT of work,
and even if the quality is, uh, debatable, the game actually works flawlessly
and you undeniably got the work done. Congrats and thanks!

## Lexicon

- Couille: testicle. That's what the players are, and the code is in
  couille.{cpp,h}
- schnuff: "thing". It's not french, it's a made up word, don't look at me like
  that
- snuf: Smurf?
- Tête de turc: a person that gets all the hate. In the game engine, the
  enemies are fighting one of the two couilles at a time, who is then called
  "la tête de turc". See `Game::tete_turc`

## When I laughed

- "couille" in the code
- "schnuff"
- Tête de turc. That's kinda informal and slang.
- `SuperListe` (=AwesomeList). And it's actually really not awesome, it's a
  `void*` based linked list with an embedded STATEFUL iterator. I'm sad I have
  to remove it to use actual vectors.
- `SuperListe::vide_porc`: empty (like a?) pork, meaning "in an unclean way".
  IDK why, the code is exactly the same as the unporked version.
- `SuperListe::supprime_porc`: removes an element of the list without freeing
  its memory (ie, it's a non-owning list)
- 'Gère les messages. Eh oui, Windows pue du cul' (Handles messages. Yeah,
  Windows' ass stinks, nota: Ben Karaban apparently works for MS now)
- A variable is named 'glorf'.
- "Gère le scrolling avec le super buffer qui marche bizarrement sur cette
  merde de GeForce." (Handles scrolling with the awesome buffer that works
  weirdly on this shitty GeForce)
- After a failed `new`, in a log message: "Nani? Not enough memory???"

## Significant differences

- The menus were a big pile of switch case in a single class. The pause menu
  and the title screen menu were just a big copy paste. I cleaned up all that.
  Take a look at `menus/`. Pause menu and title screen menu are now the same
  thing
- Added a "TOGGLE FULLSCREEN" option.
- Fixed a bug that prevented unix like os from playing. Some level descriptions
  contained path containing backslashes that failed. Now backslashes are
  handled.
- MusicBank has been reworked a lot

# Blip'n Blop
This is the source code of Blip'n Blop, a free video game for the PC released in 2002. Years after the game got released, some enthusiastic programmers asked us to open source it and here we are!

A few things to keep in mind:
- this was writen when we were still students so the code quality and the (lack of) architecture can be disturbing
- the code is mostly written in a terrible mix of french and english, which should be kind of akward to read for non french speaking people (actually, it's kind of awkward even for french people! :p )
- the various editors can be quite complicated to get working because they relied on various cryptic INI files

