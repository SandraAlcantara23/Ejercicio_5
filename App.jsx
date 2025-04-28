import { useState } from "react"
import Button from "./components/Button";

function App() {
  const [contador, setContador] = useState(0);

  //Aqui hiba el fragmento de codigo del contador (al llegar a 10 se regresa a -10)

  return (
    <div>
      <h1>No hiciste caso {contador} veces</h1>
      {contador % 2 === 0 ? (
        <p>El contador es par</p>
      ) : (
        <p>El contador es impar</p>
      )}


    <Button contador={1} mensaje={"Aumentar el contador"}  setContador ={setContador}/>
    <Button contador={-1} mensaje={"Decrementar el contador"}  setContador ={setContador}/>

      
  
    </div>
  );
}

export default App;
//Hacer que tenga estilo y el html 
// llegando a 10 reinice el contador al -10 y cuando llegue al -10 llegue al 10
