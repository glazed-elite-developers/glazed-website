import React, { useState } from 'react'

export default function Component({ startAt, message }) {
  const [counter, setCounter] = useState(startAt)

  return (
    <h1 onClick={e => setCounter(c => c + 1)}>
      {message} {counter}
    </h1>
  )
}
