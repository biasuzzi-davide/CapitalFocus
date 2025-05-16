# CapitalFocus

CapitalFocus è un'applicazione desktop sviluppata in C++ con il framework Qt per aiutarti a gestire e organizzare le destinazioni imperdibili nelle capitali europee. Questa app ti permette di catalogare facilmente luoghi di interesse come ristoranti, musei, attrazioni turistiche e altro ancora, semplificando notevolmente la pianificazione dei tuoi viaggi.

## Funzionalità principali

### 🎯 Organizzazione per categorie

* Tutti i luoghi sono suddivisi in categorie chiare e intuitive (ad esempio, ristoranti, musei, monumenti, ecc.) per consentirti una consultazione rapida e ordinata.

### 🔍 Ricerca e filtro

* Effettua ricerche rapide o filtra le destinazioni per categoria, nome o altri criteri specifici.

### 📂 Gestione dei dati

* Supporta l'importazione ed esportazione dei dati nei formati JSON e XML, facilitando backup e condivisione delle informazioni.

### 📐 Architettura polimorfica ed estendibile

* Progettata seguendo i principi della programmazione orientata agli oggetti (OOP), con particolare attenzione all'uso avanzato del polimorfismo per consentire un'estensione semplice e immediata del codice con nuove categorie e funzionalità.

### 🖥️ Interfaccia utente intuitiva

* L'interfaccia grafica è sviluppata con Qt per garantire un'esperienza d'uso moderna, fluida e user-friendly.

### 🌐 Supporto multilingua

* Facilmente adattabile per supportare più lingue, permettendo un utilizzo confortevole agli utenti internazionali.

## Tecnologie utilizzate

* **Linguaggio:** C++
* **Framework GUI:** Qt 6.2.4
* **Strumenti di compilazione:** qmake 3.1, gcc 11.3.0
* **Sistema operativo di riferimento:** Ubuntu 22.04 LTS

## Come eseguire l'applicazione

* Assicurarsi che Qt sia installato sulla propria macchina.
* Clonare il repository:

```bash
git clone https://github.com/tuo_utente/CapitalFocus.git
```

* Compilare ed eseguire il progetto:

```bash
cd CapitalFocus
qmake CapitalFocus.pro
make
./CapitalFocus
```

## Contribuire

Le pull request sono benvenute! Sentiti libero di contribuire proponendo nuove funzionalità, correggendo bug o migliorando la documentazione.

## Licenza

Questo progetto è distribuito sotto licenza MIT. Vedere il file [LICENSE](LICENSE) per maggiori informazioni.

---

Sviluppato come progetto per il corso di **Programmazione ad Oggetti**, Università di Padova, a.a. 2024/25.
