theme: QtDay 2019
footer: [https://github.com/uwerat/qskinny](https://github.com/uwerat/qskinny)


# [fit] QSkinny - A new approach
# [fit] for a QtQuick framework

^ 3 sections in this talk: Why, What and How (Is this yet another set of controls?)

---

# Who am I?

- working on Qt since 2008
- former QtNetwork maintainer
- [@peha23](https://twitter.com/peha23) on Twitter
- founder of [edelhirsch.io](https://www.edelhirsch.io)

^ I'm not the founder of QSkinny though

---

![inline](AGCO-Ui.jpeg)

image © AGCO GmbH

---

# [fit] Why
# [fit] QSkinny?

---

# Why create QSkinny?

- performance
- pure C++

^ performance (1): TQC: replacing QML with C++ in controls (QQC1 -> QQC2). Same solution is true for application code. let programmer decide what to write in QML and what in C++. We're going to see later: QQC2 are not really extensible.
^ performance (2): startup, memory, property binding changes (deferred updates etc.). Quite some work on QML is going into making it faster (QML compiler, direct binding etc.). With C++/QSkinny there is not much overhead to begin with.
^ C++ no bridging to QML needed, tooling (address sanitizers, refactoring, other IDEs except QtCreator, auto test coverage, static code checkers), debugging etc., personal preference. Quite some work from the Qt Company is going into tooling for QML; with C++ you get this for free.

^ ... as in: Why was it created?
^ Qt 5.3: V4 not fast enough
^ team background: QtWidgets and C++; QML was new
^ QtQuickControls 1: performance issues (all in QML, now deprecated)
^ QQC2: solution was to use C++ => too much QML can easily be a problem for performance.
^ QtQuickControls 2: not extensible (font, palette, locale / some of its logic is in QML)
^ => try how far you can get with own framework

---

# Why use QSkinny?

- public C++ API
- usable from QML
- runs with Qt 5.6 (LGPLv2)

^ QSkinny and QML are not mutually exclusive, programmer can decide how much of each he/she wants (including no QML)
^ mix and match C++/QML
^ LGPLv2: works with Qt 5.6; not much new on the C++ side (except Vulkan / shapes)
^ QSkinny is free software (LGPLv2; maybe MIT/BSD in the future)
^ However: It is not a general purpose toolkit yet, many controls were created to match the use case of the project

---

# [fit] What
# [fit] is QSkinny?

---

### A lightweight framework on top of the Qt scene graph

![inline](QSkinny.png)

^ Qsk / SG: synchronisation points, QtWidgets doesn't have those

---

# API example

```c++
    QskWindow window;

    auto button = new QskPushButton("push me");
    auto label = new QskTextLabel("label");
    auto box = new QskLinearBox(Qt::Vertical);

    box.addItem(button);
    box.addItem(label);

    window.addItem(box);
    window.show();
```

^ QSkinny does not only offer a C++ API, it also offers:
^ a more complete layouting system similar to the one of QtWidgets (QSizePolicy); QML is mostly anchoring. Problem with only anchoring: There is no central component that can lay out elements, also: Android (ConstraintLayout) and Apple (Auto Layout) nowadays have a constraint-based layout, and advise against hardcoding widths etc. Why? To enable different form factors; so: anchoring might be enough, but maybe not always.
^ size constraints (widthForHeight() etc.)
^ ### create box later, call addItem() 2x to demonstrate

---

# separation of implementation and styling

```
setMetric( QskSlider::Panel | QskAspect::Size, 20 );
setColor( QskPushButton::Text, QColor( Qt::green ) );
setAnimation( SoundControl::SliderControl | QskAspect::Color, duration );
```

^ ### AGCO: more flexibility wrt. styling, not only colours and metrics, but also handles etc. example checkbox: Haken vs. switch; hard to do in QML
^ ### controls werden durch delegates gezeichnet; delegates können ausgetauscht werden -> Diagramm
^ theming: 2 Stufen: 1. metrics / colors / animations, 2. Skinlets (delegates)

---

# [fit] How
# [fit] does QSkinny work?

---

# example: QskPageIndicator

// TODO: here picture of page indicator

```
QSGNode* QskPageIndicatorSkinlet::updateBulletsNode(
    const QskPageIndicator* indicator, QSGNode* node ) const
{
    for ( int i = 0; i < indicator->count(); i++ )
    {
        bulletNode = new QskBoxNode();
        (...)
    }
}
```

^ QskPageIndicator: one QObjects, one scene graph node per bullet; derives from QQuickItem; method above is called from updatePaintNode

^ ###: eher: Vgl. Anzahl QQuickItems und Szenengraphenknoten etc.
^ Vgl nicht ganz fair

---

# QtQuickControls2 PageIndicator

```
T.PageIndicator {
    (...)
    delegate: Rectangle {
        (...)
    }
}
```

^ each bullet is one QQuickItem (fine for page indicator, but think e.g. gradient stop)

---

# Thanks!

[support@qskinny.org](mailto:support@qskinny.org)
[peter@edelhirsch.io](mailto:peter@edelhirsch.io)

^ Again: Not to bash QML, but some constructive criticism is in place. The UI written with QSkinny is blazingly fast and is going into production soon, so another way is definitely possible.