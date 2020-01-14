/**
 * Dient zur Initialisierung. Zu Beginn des Programms einmal aufrufen.
 */
void io_init();


/**
 * Löscht alle bereits ausgegebenen Zeilen auf der Konsole.
 */
void io_clear();


/**
 * Wartet bis zu "timeout_ms" Milisekunden auf eine Eingabe von der Tastatur.
 *
 * Gibt den ASCII-Wert dieser Eingabe zurück, oder 0 (falls keine Taste gedrückt wurde).
 */
char io_read_key(int timeout_ms);