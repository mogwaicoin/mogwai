Mogwai Core 0.12.1
=====================

This is the official reference wallet for Mogwai digital currency and comprises the backbone of the Mogwai peer-to-peer network. You can [download Mogwai Core](https://www.mogwai.org/downloads/) or [build it yourself](#building) using the guides below.

Running
---------------------
The following are some helpful notes on how to run Mogwai on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/mogwai-qt` (GUI) or
- `bin/mogwaid` (headless)

### Windows

Unpack the files into a directory, and then run mogwai-qt.exe.

### OS X

Drag Mogwai-Qt to your applications folder, and then run Mogwai-Qt.

### Need Help?

* See the [Mogwai documentation](https://mogwaicoin.atlassian.net/wiki/display/DOC)
for help and more information.
* Ask for help on [#mogwaicoin](http://webchat.freenode.net?channels=mogwaicoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=mogwaicoin).
* Ask for help on the [MogwaiTalk](https://mogwaitalk.org/) forums.

Building
---------------------
The following are developer notes on how to build Mogwai Core on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The Mogwai Core repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Multiwallet Qt Development](multiwallet-qt.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- Source Code Documentation ***TODO***
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Unit Tests](unit-tests.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)

### Resources
* Discuss on the [MogwaiTalk](https://mogwaitalk.org/) forums, in the Development & Technical Discussion board.
* Discuss on [#mogwaicoin](http://webchat.freenode.net/?channels=mogwaicoin) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=mogwaicoin).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)

License
---------------------
Distributed under the [MIT software license](http://www.opensource.org/licenses/mit-license.php).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
