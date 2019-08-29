# HF5-Rotor
Af Nicki Bo Otte

D. 20 Aug 2019

## Beskrivelse kort
I dette projekt vil jeg få en STM32F746NG til, at rotere en motor efter hvilke svar den får fra et RESTAPI, som snakker med en database.

## Sekvens diagram
<img src="./Message Sequence Chart.svg">

## STM32F7465NG brættet
Der skal bruges 1 stk. STM32F7465NG bræt. Denne enhed skal være client i et system, hvor den vil fortælle et RESTAPI at den er tilstede, og at den vil spørge API'et om hvilke hastighed den skal dreje køre motoren. 

### Grove Gear stepper motor
Jeg vil udnytte mig af denne motor, som skal roteres via brættet: http://wiki.seeedstudio.com/Gear_Stepper_Motor_Driver_Pack/

### Sikkerhed
Det er tiltænkt at brættet skal snakke https med API'et. Som det ser ud lige nu, så er der ikke tid til, at implementere dette. Dog drejer det sig bare om, at skaffe et gyldigt certifikat og et domæne dertil til API'et.

### Bilbliotek
| Program        | Version          |
|----------------|------------------|
| mbed-os        | 5.13.2           |
| mbed-http      | a8d157986ad8     |
| MbedJSONValue  | 10a99cdf7846     |
| sMotor         | 7b7c58bb9831     |

### 3-lags model
Jeg har valgt at bygge min løsning efter 3 lags modelen, da dette giver god mulighed for skalering, og dynamik.
Jeg har lavet den, så den ser således her ud.

<img src="./3 layer model.svg">


### Data lag
Datalaget består af en flad fil database, som er en JSON fil. Denne JSON fil bliver udbygget efter en struktur jeg har valgt. Denne struktur ser således her ud.

<img src="./Relations diagram.svg">

### Business lag
Dette lag består af et API, som ærgere mellem mand for data laget og præsentationslaget.

#### REST API
##### Generalt
Dette er et REST API og det følger REST standarderne.
API'et har nogle forskellige muligheder. 

<code>POST /token</code>

Dette endpoint, kan kaldes af brættet, og det vil give en token tilbage.

<code>GET /device/{token}</code>

Dette enpoint KRÆVER en gyldig token. 
Her vil den give et JSON svar tilbage, med det objekt som er knyttet til den token som der er sndt med, som set i data laget.

<code>PATCH /device/{token}</code>

Dette enpoint KRÆVER en gyldig token. 
Dette endpoint bruges til at ændre værdien "rotateClockwise", som det enkelte bræt har på sig, når det er indregistreret i API'et.

<code>GET /devices</code>

Dette endpoint vil give en komplet json fil som set i data laget.


##### Sikkerhed
Det er tænkt sådan, at hvis man har et domæne, og et gyldigt certifikat, så er det muligt at snakke https med api'et. Dette er selvæflgelig det mest optimale at gøre. 

API'et er lavet således, at man skal spørge API'et efter en token, og man får ikke den, uden man kender en "secret". Denne secret er hardcoded ind i brættets kode. Tokenen er unik for brættet.
Denne token skal så bruges til, at hente data ud fra API'et om sit eget bræt. Den skal også bruges hvis man ønsker at rette i rotationen for api'et.


##### Webserver
For at starte webserveren skal denne kommando køres, mens man står i php_API mappen:  

``` php -S localhost:8888 -t app app/index.php ```

##### Testet software
| Program        | Version |
|----------------|---------|
| Slim framework | 4.0     |
| PHP            | 7.2     |
| Ubuntu         | 19.04   |

##### Bibiliotek
Bilbiotekket kan findes inde i package.json filen.

### Præsentations lag
Dette lag har jeg valgt, at lave en hjemmeside, som kan vise alle registrerede enheder og deres status.
Det er hertil tiltænkt, hvis der var mere tid, at lave få brættet til at vise rotationsvejen, samt 2 knapper der kan fortælle hvilken vej motoren skal rotere. 

#### Hjemmeside
##### Generelt
Jeg har lavet en hjemmeside, som viser en tabel over de indregisterede enheder. Her kan man se hvilke værdier de har, og det er tænkt man skal have mulighed for at rette på det valgte bræts rotation.

##### Webserver
For at starte webserveren skal denne kommando køres, mens man står i react_website:  

``` npm start ```

##### Testet software
| Program        | Version |
|----------------|---------|
| node.js        | 12.9.1  |
| PHP            | 6.10.2  |
| Ubuntu         | 19.04   |

##### Bibiliotek
Bilbiotekket kan findes inde i package.json filen.

# Logbog
### 20-08-2019
I dag har jeg bokset meget med at få CLion til at kunne compile et projekt. Jeg kom langt i det, men det virker for stort og indviklet, så jeg går tilbage til mbed compiler(online).

I dag er jeg kommet godt igang med at teste netværksmulighederne i mbed-os.

### 21-08-2019
I dag har jeg bokset med mbed offline cli compiler. Dette har jeg fået til at virke, så nu kan jeg compile mine .bin filer selv.
Ud over det har jeg, forsøgt mig frem med at give brættet en IP addresse, hvilket er lykkedes, og nu prøver jeg at få den til at hente JSON data fra DAWA's aws api. Dette har jeg dog problemer med, da brættet har problemer med at forstå, den gerne må bruge tls.

### 22-08-2019
I dag har jeg bokset utroligt meget med, at få TLS til at virke. Dette har jeg opgivet på, da jeg formoder, at det vil tage længere tid, at få til at virke, end jeg vil kunne nå at lave produktet. 

Jeg er af samme årsag gået igang med, at lave API'et som brættet skal snakke sammen med. Her har jeg besluttet mig for, at skulle bruge PHP, med PHP Slim framework til. PHP har en enbygget webserver, som jeg vil bruge til demo. Det skal siges, havde det været noget særiøst, havde jeg sat noget op som Apache2 eller andet.

### 23-08-2019
Jeg er i dag gået igang med, at få stepper motoren til at virke. 
Jeg har fundet et bibliotek, som vil hjælpe mig med dette. 
Bibliotekket virker, men jeg er lidt uforståen overfor hvordan dens "stepper_speed" fungere. De har ikke rigtig dokumenteret det. 
Jeg kan dog konstatere, at værdien 800 spinner motoren hurtigere end værdien 2000. Dog hvis værdien 400 er valgt, så er det som om motoren ikke kobler på. Den går med andre ord i stå.

### 26-08-2019
I dag vil jeg kigge videre på at lave API delen i PHP. Jeg vil samtidig lave den klasse, som skal snakke sammen med den, til login.
Jeg har fået lavet hele API delen, og kontrolleret at den virker. Imorgen vil jeg fokusere på at lave resten af logikken til brættet.

### 27-08-2019
I dag har jeg lavet den fulde integration, så nu gør brættet det som det skal. Nu skal jeg bare kigge koden igennem for comments, og hvis der er tid til det, så vil jeg implementere TLS Sockets.

### 28-08-2019
I dag har jeg brugt tid på at gå min kode igennem, og sørge for den er dokumenteret som jeg ønsker den.
Dernest har jeg lavet en hjemmeside mere, som køre react, som bruger API'et til at live vise en liste over værdierne.
