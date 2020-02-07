import React, { useState } from 'react'
import { css } from 'emotion'

const styles = {
  h1: css`
    font-size: 24px;
  `,
}

export default function Component({ startAt, message }) {
  const [counter, setCounter] = useState(startAt)

  return (
    <h1 className={styles.h1} onClick={e => setCounter(c => c + 1)}>
      {message} {counter}
    </h1>
  )
}
