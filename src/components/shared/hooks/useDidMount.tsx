import { useEffect, useState } from 'react'

export default function useDidMount() {
  const [didMount, setDidMount] = useState(false)
  useEffect(() => setDidMount(true), [])
  return didMount
}
