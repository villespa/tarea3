# TODO - Proyecto Juego Mazmorra

## 🚨 Urgente - Correcciones de Compilación

- [ ] **Verificar dependencias circulares** - Asegurar que las declaraciones forward estén correctas

## 🎮 Funcionalidad Core del Juego

### Sistema de Movimiento
- [x] Implementar movimiento básico del jugador
- [x] Validación de límites del mapa
- [ ] **Implementar cambio de dirección** - Agregar case 'd' en el switch del mainLoop
- [ ] **Implementar mas instrucciones del menu** 

### Sistema de Interacción
- [ ] **Implementar interacción con objetos** - Agregar case 'c' en el switch
- [ ] **Sistema de llaves y puertas** - Mecánica completa
- [ ] **Sistema de cofres** - Recompensas y objetos

### Sistema de Combate
- [ ] **Implementar ataque del jugador** - Detectar enemigos en rango
- [ ] **Sistema de dano** - Reducir vida de enemigos y del jugador
- [ ] **Sistema de habilidades** - Agregar case 'z' funcional
- [ ] **Sistema de bombas** - Destruir paredes/enemigos

## 🎯 Mecánicas de Juego

### Progresión
- [ ] **Sistema de estadísticas** - Tracking de pasos, enemigos derrotados, etc.
- [ ] **Condiciones de victoria** - Llegar al final, derrotar jefe
- [ ] **Condiciones de derrota** - Vida = 0
- [ ] **Sistema de puntuación** - Score basado en performance

### Sala del Jefe
- [ ] **Entrada a sala jefe** - Verificar llaves especiales
- [ ] **Combate con jefe** - Mecánicas especiales
- [ ] **Recompensas especiales** - Items únicos del jefe

## 🛠️ Mejoras Técnicas

### Estructura de Código
- [ ] **Refactorizar mainLoop** - Separar lógica en funciones más pequeñas
- [ ] **Mejorar manejo de errores** - Try-catch en operaciones críticas
- [ ] **Optimizar carga de archivos** - inseguro en esta parte - Cachear datos cargados
- [ ] **Documentar código** - Agregar comentarios a funciones complejas

### Interfaz de Usuario
- [ ] **Mejorar visualización del mapa** - Colores consistentes
- [ ] **Mostrar inventario** - Llaves, bombas, objetos
- [ ] **Indicadores visuales** - Salud, dirección, estado
- [ ] **Mensajes informativos** - Feedback claro de acciones

## 🐛 Bugs Conocidos

- [ ] **Coordenadas confusas** - Verificar si X/Y están intercambiados
- [ ] **Validación de movimiento** - Revisar lógica de `puedeMoverse()`
- [ ] **Manejo de entrada inválida** - Evitar crashes con inputs incorrectos
- [ ] **Memory leaks potenciales** - Verificar gestión de memoria

## 🚀 Features Adicionales (Futuro)

## 📋 Testing

### Casos de Prueba
- [ ] **Movimiento en todas las direcciones**
- [ ] **Colisión con paredes/enemigos**
- [ ] **Uso de llaves en puertas**
- [ ] **Combate básico**
- [ ] **Carga de diferentes mapas**
- [ ] **Condiciones de victoria/derrota**

### Validación de Datos
- [ ] **Archivos CSV malformados**
- [ ] **Mapas con errores**
- [ ] **Entrada de usuario inválida**

---

## 📝 Notas de Desarrollo

### Problemas Recientes Solucionados
- [x] Dependencia circular entre Jugador.h y Mazmorra.h
- [x] Errores de compilación con caracteres Unicode
- [x] Switch statement fall-through en mainLoop

### Próximos Pasos Inmediatos
1. Completar sistema de cambio de dirección
2. Implementar interacción con objetos
3. Agregar más casos al switch del mainLoop
4. Testear funcionalidad básica completa
