# 📘 Progetto Reti – Sockets TCP/UDP

## 👤 Informazioni Studente
| Voce | Dato |
|------|------|
| **Studente:** | *Antonio Palladino* |
| **Numero di Matricola:** | *825061* |
| **Email Istituzionale:** | *a.palladino10@studenti.uniba.it* |

---

## 1. Specifiche della Consegna e Ambiente di Lavoro

| Protocollo | Cartella | Sistema Operativo |
|:---------:|:--------:|:-----------------:|
| **TCP** | `TCP_G1` | Windows 11 |
| **UDP** | `UDP_G1` | Windows 11 |

I progetti sono stati sviluppati e testati su Windows 11; su altri sistemi operativi potrebbero essere necessarie modifiche.

---

## 2. 🧰 Compilazione e IDE Utilizzato (Code::Blocks)

Lo sviluppo è stato effettuato con **Code::Blocks** utilizzando il compilatore **MinGW/GCC**, su ambiente Windows 11.

Per ricompilare correttamente i file `.c` tramite Code::Blocks è obbligatorio collegare la libreria di rete **Winsock**, necessaria alle funzioni dei socket, aggiungendo:

```
Ws2_32.lib
```

---

### ⚙️ Configurazione della Libreria in Code::Blocks

Procedura da eseguire per ogni progetto:

1. Aprire il progetto in Code::Blocks.
2. Menu **Project** → **Build options...**
3. Sezione **Linker settings** → *Link libraries*
4. Aggiungere:
   ```
   ws2_32
   ```
5. Salvare e compilare.

---

### 🔎 Perché è necessario aggiungere la libreria?

La direttiva:

```c
#pragma comment(lib, "Ws2_32.lib")
```

non viene sempre interpretata dal compilatore MinGW/GCC.
Aggiungendo manualmente *ws2_32* nelle opzioni del linker si evita che funzioni come `socket()`, `bind()`, `connect()`, `sendto()` e simili producano errori in fase di linking.

---
