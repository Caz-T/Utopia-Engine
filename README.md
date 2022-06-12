# Utopia-Engine

This is an implementation of the famous Print-n'-play board game: Utopia Engine. More rules and usages are to be added here. 

This project has been submitted as my course project for OOP 2022 Spring, Tsinghua University.

If you feel like refining any part of this game, feel free to start an issue!

> For Hannah. For your future. For your inner Utopia.

## Licensing

This programme is licensed under GPL v3, as required by Qt open-source. Read LICENSE for more info.

## Installation and deployment

### M1 Mac users:

Just download Utopia-Engine.dmg and play. The .dmg package is always up-to-date (or close to up-to-date).

### Intel Mac users:

I'm not sure whether the package works fine on Intel Macs, but you can have a try. If it doesn't, you need a Qt 6.3.0 package with macdeployqt. 
Clone the source code repo, and follow the steps on https://doc.qt.io/qt-6/macos-deployment.html. It would be deployed for your computer.

### Windows users:

**I'm not sure whether this works fine, as I haven't tried these steps yet.**

Although the whole development process is solely done on my Mac, I'm quite sure the codes are compatible with Windows computers under the right configurations. I'll try to release a nice version for Windows once all debugging are done. 

You need a Qt 6.3.0 package with windeployqt. Clone the source code repo, and follow the steps on https://doc.qt.io/qt-6/windows-deployment.html. 

*Note: Some panels are found to be incorrectly set up on Windows. Performance might be undersatisfactory.*


## How to play
I apologize for not being able to elaborate on the detailed rules of the game. The game itself has a decent complexity (that's why I've been playing it for seven years and counting), so I suppose it should be left for each player to enjoy the fullest of exploring the game.

The main idea is to start an ancient mythic machine called **The Utopia Engine** before doomsday descends upon mankind. You, Isodoros, probably the only human being capable of restarting the Utopia Engine, are to find six artifacts and assemble them so as to perpetually detain doomsday. Artifacts must be found, activated and properly linked to regain their power. Eventually you are also to do a final activation to start up the Engine. The more precise you link the artifacts, the easier it'll be to do the eventual activation.

Basically it's a dice game. If you'd prefer the original offline game, all you need is just a pencil, a rubber, two six-sided dice and a printed version of the maps included in this repo.

## Credits

Thanks to the print-and-play version of Utopia Engine itself, without which I'd spend dozens of afternoons dozing off in class. 

Thanks to Nick Hayes for the elegant game design and delicate artwork throughout the game. 

Thanks to usa175@BoardGameGeek for uploading the Chinese rulebook. Thanks to 欧冶喵、地狱的傀儡师@知乎 for drafting and revising the rulebook. Their Chinese translation of proper nouns in the game shedded light on my implementation.

Thanks to all contributors to the game design of Utopia Engine, and all players that kept the community vital.


## Miscellaneous

1. I hate the class name QDialog. It lured me into naming my classes xxx_dialog rather than xxx_dialog**ue**. BrE is the cancer of modern English.
2. It's been some painful weeks physically and mentally, which provides good excuse for not making my implementation half as elegent as the original game.
3. DO NOT LEAVE A COURSE PROJECT TO ITS DEADLINE. OR YOU'LL DIE STRUGGLING.
