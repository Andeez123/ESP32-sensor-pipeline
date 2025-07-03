import { useState, useEffect} from 'react'
import reactLogo from './assets/react.svg'
import viteLogo from '/vite.svg'
import './App.css'

function App() {
  const [data, setData] = useState([]);

  useEffect(() => {
      fetch('http://192.168.68.105:5000/query')
          .then(response => response.json())
          .then(json=> setData(json))
          .catch(error => console.log(error))
  }, []);

    return (
        <div className="p-4">
            <h2 className="text-xl font-bold mb-4">Temperature Data</h2>
            <table className="w-full border-collapse border border-gray-300">
                <thead>
                <tr className="bg-gray-200">
                    <th className="border p-2">Temperature (°C)</th>
                    <th className="border p-2">Time</th>
                </tr>
                </thead>
                <tbody>
                {data.map((entry) => (
                    <tr>
                        <td className="border p-2">{entry.Temperature}</td>
                        <td className="border p-2">{entry.Time}</td>
                    </tr>
                ))}
                </tbody>
            </table>
        </div>
    );
}

export default App
