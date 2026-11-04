# Scan time of arrival

Diverse soglie, diverse coppie di canali

---

**nota**: in data/, i file a 10 mV sono in realtà a 50 mV 

---

**problema**: nella versione originale, gli elementi di alcuni branch erano, per ogni evento, dei vettori dinamici c++ (quindi vector<double>, ad esempio). nel file nuovo del run, si usano invece degli array a dimensione variabile stile c: una fila di numeri in memoria...   
per risolvere modificando minimamente, si possono usare dei puntatori tipo di appoggio (chiamati raw nel codice) "compatibili" con il file. nel fare setbranchaddress si mettono proprio gli indirizzi di memoria di queste variabili. per adattare al resto del codice, si usano poi i dati letti impacchettando i numeri raw dentro dei vettori temporanei (usando inizio, fine), e facendo poi puntare i puntatori originali a questi vettori. 

teoricamente il tutto dovrebbe funzionare, solo che c'è un problema con il ToT che nel file è un tipo UShort_t, che a quanto pare root gestisce male.