# Anti-Clog / Runout Detector (ESP32)

Detector inteligente de **atascos (clog)** y **fin de filamento (runout)** para impresoras 3D, basado en **ESP32**.  
Funciona de forma **universal**, sin depender del firmware de la impresora y sin hardware externo complejo.

Diseñado para **extrusores directos**, con un enfoque robusto y sin falsos positivos.

---

## ✨ Características principales

- ✅ Detección real de **clog** (filamento no avanza)
- ✅ Detección de **runout** (fin de filamento)
- ✅ Compatible con **cualquier impresora 3D**
- ✅ No requiere modificar el firmware de la impresora
- ✅ Funciona como **sensor de runout externo**
- ✅ Configuración simple y fiable
- ✅ Web integrada para estado y actualización
- ✅ Dos métodos de flasheo:
  - Web (recomendado)
  - Arduino IDE (usuarios avanzados)

---

## 🧠 Cómo funciona

El sistema usa:

- **1 encoder óptico** → detecta movimiento real del filamento  
- **1 microswitch** → detecta presencia de filamento  
- **ESP32** → procesa la lógica y actúa

Si:
- hay filamento **pero no hay movimiento durante un tiempo configurable** → **CLOG**
- no hay filamento → **RUNOUT**

En ambos casos, el ESP32 activa una salida que **emula un sensor de runout**, haciendo que la impresora pause automáticamente.

---

## 🔌 Hardware necesario (MVP)

- ESP32-C3 (recomendado)  
- 1 encoder óptico (3 pines: GND / 5V / OUT)  
- 1 microswitch (COM / NO)  

### Pinout por defecto
| Función | GPIO |
|------|------|
| Encoder | GPIO 2 |
| Microswitch | GPIO 4 |
| Runout OUT | GPIO 5 |
| Alimentación sensores | 5V + GND |

---

## 🚀 Instalación (RECOMENDADO – vía Web)

La forma más sencilla, **sin instalar nada**:

👉 **Web Installer oficial**  
https://harrynow83.github.io/runout-clog-detector-installer/

### Pasos
1. Abre la web desde **Chrome / Edge**
2. Conecta el ESP32 por USB
3. Pulsa **“Conectar y Flashear”**
4. Selecciona el puerto
5. Espera a que termine

Al finalizar:
- El ESP32 se reinicia
- Crea una red WiFi propia
- El firmware queda instalado

---

## 🌐 Interfaz Web integrada

Después de flashear:

1. Conéctate al WiFi:
2. Abre en el navegador:
http://192.168.4.1


Desde ahí puedes:
- Ver el estado en tiempo real
- Ver pulsos del encoder
- Detectar CLOG / RUNOUT
- Actualizar firmware vía web (OTA)

---

## 🔁 Actualización de firmware (OTA Web)

1. Conéctate al WiFi del ESP32
2. Abre:
http://192.168.4.1/update

3. Sube el archivo `firmware.bin`
4. El dispositivo se actualiza y reinicia

> No requiere cable USB después de la primera instalación.

---

## 🧑‍💻 Instalación alternativa (Arduino IDE)

Para usuarios avanzados o entornos sin Web Serial.

- El firmware para Arduino IDE está en:
firmware/arduino/

- Incluye instrucciones completas de compilación y carga.

Consulta:
firmware/arduino/README.md


---

## ⚙️ Ajustes importantes

Para extrusores directos y primeras capas lentas, se recomienda:

```cpp
#define CLOG_TIMEOUT_MS 6500
#define CONFIRM_CYCLES  3
```

Estos valores reducen falsos positivos y mantienen una detección fiable.
---
🖨️ Compatibilidad con impresoras

Funciona con:

Marlin

Klipper

RepRap

Cualquier impresora con entrada de runout

No requiere:

Plugins

Modificaciones de firmware

Conexión por red a la impresora
---
📌 Estado del proyecto

MVP funcional y probado

Arquitectura preparada para:

más sensores

más impresoras

lógica avanzada

Proyecto en desarrollo activo
---
📄 Licencia

Proyecto open-source.
Uso libre para proyectos personales y educativos.


