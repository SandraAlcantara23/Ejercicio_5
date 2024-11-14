# **Ejercicios de Funciones:**
## Calcular el salario promedio de los empleados:
 **Enunciado:** Queremos saber cuál es el salario promedio de los empleados en la empresa Calcula este valor utilizando una función agregada adecuada.
 ```sql
  SELECT AVG(salary) AS promedio_sueldo FROM empleados;
 ```
# **Contar el número de empleados en cada departamento:**
 **Enunciado:** Deseamos saber cuántos empleados trabajan en cada departamento. Para ello,
 necesitas agrupar a los empleados por departamento y contar cuántos hay en cada uno.
 ```sql
SELECT department, COUNT(*) AS total_empleados 
FROM empleados 
GROUP BY department;
 ```
 # **Encontrar el salario más alto y más bajo:**
  **Enunciado:** La gerencia quiere conocer el salario más alto. 
  ```sql
 SELECT MAX(salary) AS salario_maximo FROM empleados;
  ```
  Salario más bajo entre todos los empleados.
  ```sql
 SELECT MIN(salary) AS salario_minimo FROM empleados;
  ```
  # **Convertir los nombres de los empleados a mayúsculas:**
   **Enunciado:** Se necesita una lista de todos los nombres de empleados convertidos a mayúsculas.
```sql
 SELECT UCASE(nombre) AS nombre_mayusculas FROM empleados;
```
# **Obtener la longitud de los nombres de los empleados:**
 **Enunciado:** Queremos saber la longitud (número de caracteres) de los nombres de todos los
 empleados.
 ```sql
 SELECT LENGTH(nombre) AS longitud_nombre FROM empleados;
 ```
# **Extraer las primeras tres letras de cada nombre:**
 **Enunciado:** Para un análisis de iniciales, necesitamos extraer las primeras tres letras del nombre
 de cada empleado.
  ```sql
   SELECT MID(nombre, 1, 3) AS iniciales FROM empleados;
 ```
 # **Formatear los salarios a dos decimales:**
  **Enunciado:** Queremos mostrar los salarios de los empleados formateados con dos decimales de
 manera clara y legible.
 ```sql
    SELECT FORMAT(salary, 2) AS salario_formateado FROM empleados;
 ```
# **Obtener la fecha actual y calcular el tiempo desde el ingreso:**
 **Enunciado:** Queremos saber cuánto tiempo ha pasado (en días) desde que cada empleado
 ingresó a la empresa hasta la fecha actual.
```sql
    SELECT DATE(NOW()) AS fecha_actual;
 ```
 # **Contar cuántos empleados tienen su nombre más largo de 10 caracteres**
  **Enunciado:** Necesitamos contar cuántos empleados tienen un nombre con más de 10 caracteres.
```sql
SELECT COUNT(*) AS empleados_mas_de_10_caracteres
FROM empleados 
WHERE LENGTH(nombre) > 10;
 ```
 # **Filtrar empleados que ingresaron hace más de 5 años:**
  Enunciado: Queremos obtener una lista de empleados que hayan ingresado hace más de 5
 años
```sql
SELECT nombre fecha_ingreso
FROM empleados
WHERE fecha_ingreso < DATE_SUB(CURDATE(), INTERVAL 5 YEAR);
 ```